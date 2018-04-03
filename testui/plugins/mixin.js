import Vue from 'vue'
Vue.mixin({
  methods: {
    async restart() {
      this.isLoading = true
      try {
        var result = await this.$axios.get('api/stdcvt/restart')
        var msg = '재시작 완료 했습니다'
      } catch (error) {
        console.log(error)
        msg = '재시작 실패 했습니다'
      }

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          msg, {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result !== undefined && result.status === 200) {}
      }, 500)
    },
    async update() {
      this.isLoading = true
      try {
        var result = await this.$axios.get('api/stdcvt/update')
        var msg = '업데이트 완료 했습니다'
      } catch (error) {
        console.log(error)
        msg = '업데이트 실패 했습니다'
      }

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          msg, {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result !== undefined && result.status === 200) {}
      }, 500)
    }
  }
})
