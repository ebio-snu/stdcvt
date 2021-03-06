var path = require('path')
const apiStdcvt = require('./api/stdcvt.js')
const express = require('express')
const bodyParser = require('body-parser')
var cors = require('cors')

const {
  Nuxt,
  Builder
} = require('nuxt')
const app = express()
app.use(cors())
const port = process.env.PORT || 8880 
const ip = process.env.IP
console.log("ip : ", ip)

global.appRoot = path.resolve(__dirname, '../')

// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({
  extended: false
}))
// parse application/json
app.use(bodyParser.json())

app.set('ip', ip)
app.set('port', port)

// Import API Routes
app.use('/api', apiStdcvt)

// Import and Set Nuxt.js options
let config = require('../nuxt.config.js')
config.dev = !(process.env.NODE_ENV === 'production')

async function start() {
  // Init Nuxt.js
  const nuxt = new Nuxt(config)

  // Build only in dev mode
  if (config.dev) {
    const builder = new Builder(nuxt)
    await builder.build()
  }

  // Give nuxt middleware to express
  app.use(nuxt.render)

  // Listen the server
  // app.listen(port, host)
  app.listen(port, function () {
    console.log('Server listening on port: ' + port)
  })
}
start()
