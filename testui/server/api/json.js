const jsonfile = require('jsonfile')
const express = require('express')
const router = express.Router()
var path = require('path')

router.get('/json', function (req, res) {
  const apilist = jsonfile.readFileSync(path.join(appRoot, 'ui/apilist.json'))
  const command = jsonfile.readFileSync(path.join(appRoot, 'ui/command.json'))
  var stdcvt = jsonfile.readFileSync(path.join(appRoot, '/ui/stdcvt.json'))
  const value = jsonfile.readFileSync(path.join(appRoot, 'ui/value.json'))

  res.json({
    apilist, command, stdcvt, value
  })
})

router.get('/json/default', function (req, res) {
  try {
    const stdcvt = jsonfile.readFileSync(path.join(appRoot, 'ui/stdcvt.json'))
    var stdcvtBackup = JSON.parse(JSON.stringify(stdcvt))
    try {
      jsonfile.writeFileSync(path.join(appRoot, 'ui/stdcvt_backup.json'), stdcvtBackup, { spaces: 2 })
      stdcvt.upapi = {}
      stdcvt.downapi = {}
      jsonfile.writeFileSync(path.join(appRoot, 'ui/stdcvt.json'), stdcvt, { spaces: 2 })
      res.sendStatus(200)
    } catch (error) {
      jsonfile.writeFileSync(path.join(appRoot, 'ui/stdcvt.json'), stdcvtBackup, { spaces: 2 })
      res.sendStatus(500)
    }
  } catch (error) {
    res.sendStatus(500)
  }
})

router.get('/json/:file', function (req, res) {
  const json = jsonfile.readFileSync(path.join(appRoot, 'ui/' + req.params.file + '.json'))
  res.json(
    json
  )
})

router.post('/json/:file', function (req, res) {
  console.log(req.body)

  jsonfile.writeFile(path.join(appRoot, 'ui/' + req.params.file + '.json'), req.body, { spaces: 2 }, function (err) {
    if (err) {
      res.sendStatus(500)
    } else {
      res.sendStatus(200)
    }
  })
})

router.post('/jsons', function (req, res) {
  try {
    let oriJson = {}
    oriJson.stdcvt = jsonfile.readFileSync(path.join(appRoot, 'ui/stdcvt.json'))
    oriJson.command = jsonfile.readFileSync(path.join(appRoot, 'ui/command.json'))
    try {
      jsonfile.writeFileSync(path.join(appRoot, 'ui/stdcvt.json'), req.body.stdcvt, { spaces: 2 })
      jsonfile.writeFileSync(path.join(appRoot, 'ui/command.json'), req.body.command, { spaces: 2 })
      res.sendStatus(200)
    } catch (error) {
      jsonfile.writeFileSync(path.join(appRoot, 'ui/stdcvt.json'), oriJson.stdcvt, { spaces: 2 })
      jsonfile.writeFileSync(path.join(appRoot, 'ui/command.json'), oriJson.command, { spaces: 2 })
      res.sendStatus(500)
    }
  } catch (error) {
    res.sendStatus(500)
  }
})

router.get('/update', function (req, res) {
  res.sendStatus(200)
})

router.get('/restart', function (req, res) {
  res.sendStatus(200)
})

module.exports = router
