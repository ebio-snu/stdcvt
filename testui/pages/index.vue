<template>
  <section>

    <div class="container-fluid">
      <div class="card mt-3 mb-3">
        <div class="card-header">
          <div class="row">
            <div class="navbar">Driver</div>
            <div class="col" style="text-align: right; padding-right: 0px;">
              <button style="padding-left: 2px;padding-right: 2px;" type="button" class="btn btn-primary btn-sm mr-2" @click="restart">Update</button>
              <button style="padding-left: 2px;padding-right: 2px;" type="button" class="btn btn-warning btn-sm mr-2" @click="update">Restart</button>
              <button style="padding-left: 2px;padding-right: 2px;" type="button" class="btn btn-success btn-sm mr-2" @click="defaultData">Default</button>
              <button style="padding-left: 2px;padding-right: 2px;" type="button" class="btn btn-info btn-sm mr-2" @click="saveData">Save</button>
            </div>
          </div>
        </div>
        <div class="card-body">
          <div class="row">
            <div class="col-lg-6">
              <div style="text-align: center;">SSDRIVER
              </div>
              파일명
              <b-form-select class="mb-4 mt-2" value-field="driver" text-field="driver" v-model="driveSsdSelected" :options="mainDatas.driverlist.ssdriver">
              </b-form-select>
              옵션
              <jsoneditor class="mt-2" v-model="getDriveOpSsd" mode="code" @json-error="ssdErrorChg" />

            </div>
            <div class=" col-lg-6 ">
              <div class="d-lg-none"><hr></div>
              <div style="text-align: center;">DSDRIVER
              </div>
              파일명
              <b-form-select class="mb-4 mt-2" value-field="driver" text-field="driver" v-model="driveDsdSelected" :options="mainDatas.driverlist.dsdriver">
              </b-form-select>
              옵션
              <jsoneditor class="mt-2" v-model="getDriveOpDsd" mode="code" @json-error="dsdErrorChg" />

            </div>
          </div>
        </div>

      </div>

      <BlockUI message="Loading..." v-show="isLoading "></BlockUI>
    </div>
  </section>
</template>

<script>
export default {
  components: {},
  async asyncData({ app }) {
    let mainDatas = await app.$axios.$get('api/stdcvt', {})
    app.store.commit('newVersion', mainDatas.stdcvt.stdcvt.version)

    let driveSsdriverNewOption = mainDatas.driverlist.ssdriver[0].option
    let driveSsdriverSelected = mainDatas.driverlist.ssdriver[0].driver

    let driveDsdriverNewOption = mainDatas.driverlist.dsdriver[0].option
    let driveDsdriverSelected = mainDatas.driverlist.dsdriver[0].driver

    if (mainDatas.stdcvt.ssdriver) {
      driveSsdriverNewOption =
        mainDatas.stdcvt.ssdriver.length > 0
          ? mainDatas.stdcvt.ssdriver[0].option
          : mainDatas.driverlist.ssdriver[0].option
      driveSsdriverSelected =
        mainDatas.stdcvt.ssdriver.length > 0
          ? mainDatas.stdcvt.ssdriver[0].driver
          : mainDatas.driverlist.ssdriver[0].driver
    }

    if (mainDatas.stdcvt.dsdriver) {
      driveDsdriverNewOption =
        mainDatas.stdcvt.dsdriver.length > 0
          ? mainDatas.stdcvt.dsdriver[0].option
          : mainDatas.driverlist.dsdriver[0].option
      driveDsdriverSelected =
        mainDatas.stdcvt.dsdriver.length > 0
          ? mainDatas.stdcvt.dsdriver[0].driver
          : mainDatas.driverlist.dsdriver[0].driver
    }

    return {
      mainDatas: mainDatas,
      drive_ssdriver_selected: driveSsdriverSelected,
      drive_ssdriver_new_option: driveSsdriverNewOption,
      drive_dsdriver_selected: driveDsdriverSelected,
      drive_dsdriver_new_option: driveDsdriverNewOption
    }
  },
  data() {
    return {
      isLoading: false,
      valueInterVal: Function,
      saveObject: {},
      ssdError: false,
      dsdError: false
    }
  },
  mounted: function () {},
  beforeDestroy: function () {
    clearTimeout(this.valueInterVal)
  },
  methods: {
    ssdErrorChg(error) {
      this.ssdError = error
    },
    dsdErrorChg(error) {
      this.dsdError = error
    },
    async defaultData() {
      this.isLoading = true
      let result = 'Error'
      try {
        result = await this.$axios.$get('api/stdcvt/default', {})
      } catch (error) {}

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result === 'OK'
            ? '설정을 초기화 했습니다'
            : '설정 초기화 실패 했습니다',
          {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result === 'OK') {
          this.getJsonAll()
        }
      }, 500)
    },
    async saveData() {
      if (this.ssdError || this.dsdError) {
        alert('Json 형식이 잘못 되어있습니다 확인해 주세요.')
        return
      }
      this.isLoading = true

      if (this.mainDatas.stdcvt.ssdriver.length > 0) {
        this.mainDatas.stdcvt.ssdriver[0].driver = this.drive_ssdriver_selected
        this.mainDatas.stdcvt.ssdriver[0].option = this.drive_ssdriver_new_option
      } else {
        let temp = {}
        temp['driver'] = this.drive_ssdriver_selected
        temp['option'] = this.drive_ssdriver_new_option
        this.mainDatas.stdcvt.ssdriver.push(temp)
      }

      if (this.mainDatas.stdcvt.dsdriver.length > 0) {
        this.mainDatas.stdcvt.dsdriver[0].driver = this.drive_dsdriver_selected
        this.mainDatas.stdcvt.dsdriver[0].option = this.drive_dsdriver_new_option
      } else {
        let temp = {}
        temp['driver'] = this.drive_dsdriver_selected
        temp['option'] = this.drive_dsdriver_new_option
        this.mainDatas.stdcvt.dsdriver.push(temp)
      }

      try {
        var result = await this.$axios.post(
          'api/stdcvt/stdcvt',
          this.mainDatas.stdcvt
        )
      } catch (error) {}

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result.status === 200
            ? '설정 변경을 완료 했습니다'
            : '설정 변경을 실패 했습니다',
          {
            theme: 'outline',
            position: 'top-right',
            duration: 2000
          }
        )
        if (result.status === 200) {
          this.getJsonAll()
        }
      }, 500)
    },
    async getJsonAll() {
      try {
        let mainDatas = await this.$axios.$get('api/stdcvt', {})
        this.mainDatas = mainDatas

        this.drive_ssdriver_new_option = mainDatas.driverlist.ssdriver[0].option
        this.drive_ssdriver_selected = mainDatas.driverlist.ssdriver[0].driver

        this.drive_dsdriver_new_option = mainDatas.driverlist.dsdriver[0].option
        this.drive_dsdriver_selected = mainDatas.driverlist.dsdriver[0].driver

        if (mainDatas.stdcvt.ssdriver) {
          this.drive_ssdriver_new_option =
            mainDatas.stdcvt.ssdriver.length > 0
              ? mainDatas.stdcvt.ssdriver[0].option
              : mainDatas.driverlist.ssdriver[0].option
          this.drive_ssdriver_selected =
            mainDatas.stdcvt.ssdriver.length > 0
              ? mainDatas.stdcvt.ssdriver[0].driver
              : mainDatas.driverlist.ssdriver[0].driver
        }

        if (mainDatas.stdcvt.dsdriver) {
          this.drive_dsdriver_new_option =
            mainDatas.stdcvt.dsdriver.length > 0
              ? mainDatas.stdcvt.dsdriver[0].option
              : mainDatas.driverlist.dsdriver[0].option
          this.drive_dsdriver_selected =
            mainDatas.stdcvt.dsdriver.length > 0
              ? mainDatas.stdcvt.dsdriver[0].driver
              : mainDatas.driverlist.dsdriver[0].driver
        }
      } catch (error) {}
    }
  },
  watch: {},
  computed: {
    driveSsdSelected: {
      get() {
        return this.drive_ssdriver_selected
      },
      set(newValue) {
        this.drive_ssdriver_selected = newValue

        if (
          this.mainDatas.stdcvt.ssdriver &&
          this.mainDatas.stdcvt.ssdriver.length > 0 &&
          this.mainDatas.stdcvt.ssdriver[0].option &&
          this.mainDatas.stdcvt.ssdriver[0].driver ===
            this.drive_ssdriver_selected
        ) {
          this.drive_ssdriver_new_option = this.mainDatas.stdcvt.ssdriver[0].option
        } else {
          for (const element of this.mainDatas.driverlist.ssdriver) {
            if (element.driver === this.drive_ssdriver_selected) {
              this.drive_ssdriver_new_option = element.option
              break
            }
          }
        }
      }
    },
    driveDsdSelected: {
      get() {
        return this.drive_dsdriver_selected
      },
      set(newValue) {
        this.drive_dsdriver_selected = newValue

        if (
          this.mainDatas.stdcvt.dsdriver[0].option &&
          this.mainDatas.stdcvt.dsdriver[0].driver ===
            this.drive_dsdriver_selected
        ) {
          this.drive_dsdriver_new_option = this.mainDatas.stdcvt.dsdriver[0].option
        } else {
          for (const element of this.mainDatas.driverlist.dsdriver) {
            if (element.driver === this.drive_dsdriver_selected) {
              this.drive_dsdriver_new_option = element.option
              break
            }
          }
        }
      }
    },
    getDriveOpSsd: {
      get() {
        return this.drive_ssdriver_new_option
      },
      set(newValue) {
        this.drive_ssdriver_new_option = newValue
      }
    },
    getDriveOpDsd: {
      get() {
        return this.drive_dsdriver_new_option
      },
      set(newValue) {
        this.drive_dsdriver_new_option = newValue
      }
    }
  }
}
</script>



<style>
.container {
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  text-align: center;
}
.table td {
  text-align: center;
}

.hr {
  -moz-border-bottom-colors: none;
  -moz-border-left-colors: none;
  -moz-border-right-colors: none;
  -moz-border-top-colors: none;
  border-color: #eeeeee -moz-use-text-color #ffffff;
  border-style: solid none;
  border-width: 1px 0;
  margin: 18px 0;
}

.jsoneditor-vue {
  height: 450px;
}
</style>
