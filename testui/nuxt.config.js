const pkg = require('./package')

module.exports = {
  mode: 'universal',

  /*
   ** Headers of the page
   */
  head: {
    title: pkg.name,
    meta: [{
      charset: 'utf-8'
    },
    {
      name: 'viewport',
      content: 'width=device-width, initial-scale=1'
    },
    {
      hid: 'description',
      name: 'description',
      content: pkg.description
    }
    ],
    link: [{
      rel: 'icon',
      type: 'image/x-icon',
      href: '/favicon.ico'
    }]
  },

  /*
   ** Customize the progress-bar color
   */
  loading: {
    color: '#3B8070'
  },

  /*
   ** Global CSS
   */
  css: [
    'jsoneditor/dist/jsoneditor.css'
  ],

  /*
   ** Plugins to load before mounting the App
   */
  plugins: [{
    src: '~/plugins/block-ui',
    ssr: false
  },
  {
    src: '~/plugins/toast',
    ssr: false
  },
  {
    src: '~/plugins/jsoneditor',
    ssr: false
  },
  {
    src: '~/plugins/mixin',
    ssr: false
  }
  ],

  /*
   ** Nuxt.js modules
   */
  modules: [
    // Doc: https://github.com/nuxt-community/axios-module#usage
    //'@nuxtjs/axios',
    // Doc: https://bootstrap-vue.js.org/docs/
    'bootstrap-vue/nuxt'
  ],

  /*
   ** Axios module configuration
  axios: {
    proxy: true
  },
  proxy: {
    //'/api/stdcvt' : 'http://' + process.env.IP + ':8880/api/stdcvt'
    '/' : 'http://' + process.env.IP + ':8880'
  },
   */

  /*
   ** Build configuration
   */
  build: {
    /*
     ** You can extend webpack config here
     */
    extend(config, ctx) {
      // Run ESLint on save
      config.devtool = 'eval-source-map'
      if (ctx.isDev && ctx.isClient) {
        config.module.rules.push({
          enforce: 'pre',
          test: /\.(js|vue)$/,
          loader: 'eslint-loader',
          exclude: /(node_modules)/
        })
      }
    }
  }
}
