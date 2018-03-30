import Vue from 'vue'
Vue.mixin({
  methods: {
    async restart() {
      this.isLoading = true
      try {
        var result = await this.$axios.get('api/stdcvt/restart')
      } catch (error) {}

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result.status === 200 ? '재시작 완료 했습니다' : '재시작 실패 했습니다', {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result.status === 200) {}
      }, 500)
    },
    async update() {
      this.isLoading = true
      try {
        var result = await this.$axios.get('api/stdcvt/update')
      } catch (error) {}

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result.status === 200 ? '업데이트 완료 했습니다' : '업데이트 실패 했습니다', {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result.status === 200) {}
      }, 500)
    }
  }
})
