//import axios from 'axios'

//export default axios.create({
//  baseURL: 'http://' + process.env.IP + ':8880'
//})

//Vue.use(axios)

export default function ({ $axios}) {
  if (process.server)
    $axios.defaults.baseURL = 'http://' + process.env.IP + ':8880'
}
