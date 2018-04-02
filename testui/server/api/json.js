var mysql = require('mysql2/promise')
var jsonfile = require('jsonfile')
var express = require('express')
var router = express.Router()
var path = require('path')
var fs = require('fs')
var exec = require('child_process').exec

var pool = mysql.createPool({
  host: 'localhost',
  user: 'ssdriver',
  password: 'sssample',
  database: 'sssample'
})

async function getvalue() {
  try {
    const [rows] = await pool.query('select id, devtype, section, target, status, value, unit from devices')
    return rows
  } catch (error) {
    console.log(error)
  }
}

async function getcommand() {
  try {
    const [rows] = await await pool.query('select id, devtype, section, target, onoff, ratio from commands')
    return rows
  } catch (error) {
    console.log(error)
  }
}

async function insertcommand(command) {
  try {
    const [results] = await pool.query('insert into commands set ?', command)
    console.log('newcommand')
    console.log(results.insertId)
    return results.insertId
  } catch (error) {
    console.log(error)
  }
}

// configuration files
var DRIVERLIST = '../conf/driverlist.json'
var STDCVT = '../conf/stdcvt.json'
var STDCVTBACKUP = '../conf/stdcvt_backup.json'
var SENSORINFO = '../conf/sensorinfo.json'

router.get('/stdcvt', async function (req, res) {
  res.json({
    'driverlist': jsonfile.readFileSync(path.join(appRoot, DRIVERLIST)),
    'stdcvt': jsonfile.readFileSync(path.join(appRoot, STDCVT)),
    'command': await getcommand(),
    'value': await getvalue()
  })
})

router.get('/stdcvt/default', function (req, res) {
  try {
    var stdcvt = jsonfile.readFileSync(path.join(appRoot, STDCVT))
    fs.copyFileSync(path.join(appRoot, STDCVT), path.join(appRoot, STDCVTBACKUP))
    stdcvt.ssdriver = []
    stdcvt.dsdriver = []
    jsonfile.writeFileSync(path.join(appRoot, STDCVT), stdcvt, {
      spaces: 2
    })
    res.sendStatus(200)
  } catch (error) {
    res.sendStatus(500)
  }
})

router.get('/stdcvt/value', function (req, res) {
  res.json(getvalue())
})

router.post('/stdcvt/command', async function (req, res) {
  const result = await insertcommand(req.body)
  if (result !== undefined) {
    res.status(200).send(result)
  } else {
    res.sendStatus(500)
  }
})

router.post('/stdcvt/stdcvt', function (req, res) {
  try {
    jsonfile.writeFileSync(path.join(appRoot, STDCVT), req.body, {
      spaces: 2
    })
    res.sendStatus(200)
  } catch (error) {
    res.sendStatus(500)
  }
})

router.get('/stdcvt/update', function (req, res) {
  console.log('update : git pull & compile')
  var child = exec('../scripts/update', 
    function (error, stdout, stderr) {
      if (error !== null) {
        console.log('update error: ' + error)
        res.sendStatus(500)
      } else {
        console.log('update success.')
        res.sendStatus(200)
      }
    }
  );
})

router.get('/stdcvt/restart', function (req, res) {
  console.log('update : service stdcvt restart')
  var child = exec('service stdcvt restart', 
    function (error, stdout, stderr) {
      if (error !== null) {
        console.log('update error: ' + error)
        res.sendStatus(500)
      } else {
        console.log('update success.')
        res.sendStatus(200)
      }
    }
  );
})

router.get('/stdcvt/info', function (req, res) {
  res.json(jsonfile.readFileSync(path.join(appRoot, SENSORINFO)))
})

module.exports = router
