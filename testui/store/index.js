import Vuex from 'vuex'

const createStore = () => {
  return new Vuex.Store({
    state: {
      version: '1.0.0'
    },
    mutations: {
      newVersion(state, version) {
        state.version = version
      }
    }
  })
}

export default createStore
