import axios from 'axios'

export default axios.create({
    baseURL: 'http://' + process.env.IP + ':8880'
})
