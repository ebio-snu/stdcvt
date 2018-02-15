<template>
  <section class="container">
    <div class="card  mt-3 mb-3">
      <div class="card-header">
        <table style="width:100%">
          <tbody>
            <tr>
              <td>
                <h4 style="margin-bottom:0px;">ICT&nbsp;&nbsp;v.{{mainDatas.stdcvt.version}}</h4>
              </td>
              <td style="text-align:right;">

                <button type="button" class="btn btn-primary mr-2" @click="restart">Update</button>
                <button type="button" class="btn btn-warning mr-2" @click="update">Restart</button>
                <button type="button" class="btn btn-success mr-2" @click="defaultData">Default</button>
                <button type="button" class="btn btn-info mr-2" @click="saveData">Save</button>

              </td>
            </tr>
          </tbody>
        </table>

      </div>
      <div class="card-block" style="padding-bottom: 0px;padding-left: 0px;padding-top: 0px;padding-right: 0px;">
        <table class="table">
          <thead>
            <tr>
              <th scope="col" width="10%"></th>
              <th scope="col" width="20%"></th>
              <th scope="col" width="35%">Up</th>
              <th scope="col" width="35%">Down</th>
            </tr>
          </thead>
          <tbody>
            <tr class="spacer">
              <th scope="row" style="vertical-align:middle;">드라이버</th>
              <td>
                <p style="margin-top: 8px;">파일명</p>
                <p style="margin-top: 8px;">옵션</p>
              </td>
              <td>
                <b-form-select value-field="driver" text-field="driver" v-model="driveUpSelected" :options="mainDatas.apilist.upapi">
                </b-form-select>
                <textarea class="form-control mt-2" rows="5" v-model="getDriveOpUp"></textarea>
              </td>
              <td>
                <b-form-select value-field="driver" text-field="driver" v-model="driveDownSelected" :options="mainDatas.apilist.downapi">
                </b-form-select>
                <textarea class="form-control mt-2" rows="5" v-model="getDriveOpDown"></textarea>
              </td>
            </tr>
            <tr>
              <th scope="row" style="vertical-align:middle;">센서</th>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(sensor,index) in mainDatas.stdcvt.sensors" :key="index">
                      <td style="border-top:0px" width="30%">
                        <input type="text" class="form-control" v-model="sensor.name">
                      </td>

                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(sensor,index) in mainDatas.stdcvt.sensors" :key="index">
                      <td style="border-top:0px" width="30%">
                        <input type="text" class="form-control" v-model="sensor.up" max="100" min="0">
                      </td>
                      <td style="border-top:0px" width="40%">
                        <input type="number" class="form-control" placeholder="value" disabled :value="getSensorData(sensor.oriup,'up')">
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(sensor,index) in mainDatas.stdcvt.sensors" :key="index">
                      <td style="border-top:0px" width="50%">
                        <input type="text" class="form-control" v-model="sensor.down">
                      </td>
                      <td style="border-top:0px" width="50%">
                        <input type="number" class="form-control" placeholder="value" disabled :value="getSensorData(sensor.oridown,'down')">
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
            </tr>
            <tr>
              <th scope="row" style="vertical-align:middle;">개폐기</th>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(motor,index) in mainDatas.stdcvt.motors" :key="index">
                      <td style="border-top:0px" width="25%">
                        <input type="text" class="form-control" v-model="motor.name">
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(motor,index) in mainDatas.stdcvt.motors" :key="index">
                      <td style="border-top:0px" width="25%">
                        <input type="text" class="form-control" v-model="motor.up">
                      </td>
                      <td style="border-top:0px" width="35%">
                        <div class="input-group">
                          <input type="number" min="0" max="100" class="form-control" placeholder="value" @input="e => setMotorUpData(motor.oriup,'target',e.target.value)" v-bind:value="getMotorUpData(motor.oriup,'target')">
                          <div class="input-group-append">
                            <button class="btn btn-outline-primary" :class="{active: getMotorUpData(motor.oriup,'command') === '작동' ? true : false}" type="button" style="box-shadow:0 0 0 0" @click="setMotorUpData(motor.oriup,'command','on')">작동</button>
                            <button class="btn btn-outline-secondary" :class="{active: getMotorUpData(motor.oriup,'command') === '정지' ? true : false}" type="button" style="box-shadow:0 0 0 0" @click="setMotorUpData(motor.oriup,'command','off')">정지</button>
                          </div>
                        </div>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(motor,index) in mainDatas.stdcvt.motors" :key="index">
                      <td style="border-top:0px" width="50%">
                        <input type="text" class="form-control" v-model="motor.down">
                      </td>
                      <td style="border-top:0px" width="50%">
                        <div class="input-group">
                          <input type="text" class="form-control" placeholder="" disabled :value="getMotorDownCurrent(motor.oridown)">
                          <div class="input-group-append">
                            <label class="input-group-text">{{getMotorDownStatus(motor.oridown)}}</label>
                          </div>
                        </div>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
            </tr>
            <tr>
              <th scope="row" style="vertical-align:middle;">스위치</th>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(element,index) in mainDatas.stdcvt.switch" :key="index">
                      <td style="border-top:0px" width="30%">
                        <input type="text" class="form-control" v-model="element.name">
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100%">
                  <tbody>
                    <tr v-for="(element,index) in mainDatas.stdcvt.switch" :key="index">
                      <td style="border-top:0px" width="30%">
                        <input type="text" class="form-control" v-model="element.up">
                      </td>
                      <td style="border-top:0px;text-align:right;" width="40%">
                        <div class="btn-group" data-toggle="buttons">
                          <button class="btn btn-outline-primary" :class="{active: getSwitchUpData(element.oriup,'command') === '작동' ? true : false}" type="button" style="box-shadow:0 0 0 0" @click="setSwitchUpData(element.oriup,'command','on')">작동</button>
                          <button class="btn btn-outline-secondary" :class="{active: getSwitchUpData(element.oriup,'command') === '정지' ? true : false}" type="button" style="box-shadow:0 0 0 0" @click="setSwitchUpData(element.oriup,'command','off')">정지</button>
                        </div>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
              <td>
                <table width="100% ">
                  <tbody>
                    <tr v-for="(element,index) in mainDatas.stdcvt.switch " :key="index ">
                      <td style="border-top:0px " width="50% ">
                        <input type="text " class="form-control " v-model="element.down">
                      </td>
                      <td style="border-top:0px " width="50% ">
                        <button type="button " class="input-group-text btn-block ">{{getSwitchDownData(element.oridown)}}</button>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </td>
            </tr>

          </tbody>
        </table>
      </div>
    </div>
    <BlockUI message="Loading..." v-show="isLoading"></BlockUI>
  </section>
</template>

<script>
export default {
  async asyncData({ app }) {
    let mainDatas = await app.$axios.$get('json', {})

    for (const sensor of mainDatas.stdcvt.sensors) {
      sensor.oriup = sensor.up
      sensor.oridown = sensor.down
    }

    for (const motor of mainDatas.stdcvt.motors) {
      motor.oriup = motor.up
      motor.oridown = motor.down
    }

    for (const element of mainDatas.stdcvt.switch) {
      element.oriup = element.up
      element.oridown = element.down
    }

    return {
      mainDatas: mainDatas,
      drive_up_new_option: mainDatas.stdcvt.upapi.option
        ? mainDatas.stdcvt.upapi.option
        : mainDatas.apilist.upapi[0].option,
      drive_down_new_option: mainDatas.stdcvt.downapi.option
        ? mainDatas.stdcvt.downapi.option
        : mainDatas.apilist.downapi[0].option,
      drive_up_selected: mainDatas.stdcvt.upapi.driver
        ? mainDatas.stdcvt.upapi.driver
        : mainDatas.apilist.upapi[0].driver,
      drive_down_selected: mainDatas.stdcvt.downapi.driver
        ? mainDatas.stdcvt.downapi.driver
        : mainDatas.apilist.downapi[0].driver
    }
  },
  data() {
    return {
      isLoading: false,
      valueInterVal: Function,
      saveObject: {}
    }
  },
  mounted: function () {
    this.$nextTick(function () {
      this.valueInterVal = setInterval(() => {
        this.getJson('value')
      }, 10000)
    })
  },
  beforeDestroy: function () {
    clearTimeout(this.valueInterVal)
  },
  methods: {
    dataValidation(value) {
      if (value > 100) {
        alert('over')
        value = 0
      }
    },
    async defaultData() {
      this.isLoading = true
      const result = await this.$axios.$get('json/default', {})

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result === 'OK' ? '설정을 초기화 했습니다' : '설정 초기화 실패 했습니다',
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
      this.isLoading = true

      this.mainDatas.stdcvt.upapi.driver = this.drive_up_selected
      this.mainDatas.stdcvt.downapi.driver = this.drive_down_selected

      this.mainDatas.stdcvt.upapi.option = this.drive_up_new_option
      this.mainDatas.stdcvt.downapi.option = this.drive_down_new_option

      for (const sensor of this.mainDatas.stdcvt.sensors) {
        delete sensor.oriup
        delete sensor.oridown
      }

      for (const motor of this.mainDatas.stdcvt.motors) {
        for (const motorCommand of this.mainDatas.command.motors) {
          if (motorCommand.up === motor.oriup) {
            motorCommand.up = motor.up
          }
          if (motorCommand.down === motor.oridown) {
            motorCommand.down = motor.down
          }
        }
        delete motor.oriup
        delete motor.oridown
      }

      for (const element of this.mainDatas.stdcvt.switch) {
        for (const elementSwitch of this.mainDatas.command.switch) {
          if (elementSwitch.up === element.oriup) {
            elementSwitch.up = element.up
          }
          if (elementSwitch.down === element.oridown) {
            elementSwitch.down = element.down
          }
        }
        delete element.oriup
        delete element.oridown
      }

      const result = await this.$axios.$post('jsons', {
        stdcvt: this.mainDatas.stdcvt,
        command: this.mainDatas.command
      })

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(
          result === 'OK' ? '설정 변경을 완료 했습니다' : '설정 변경을 실패 했습니다',
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
    async restart() {
      await this.$axios.$get('restart')
    },
    async update() {
      await this.$axios.$get('update')
    },
    async getJsonAll() {
      this.$set(this, 'mainDatas', await this.$axios.$get('json', {}))

      if (this.mainDatas.stdcvt.upapi.driver) {
        this.drive_up_new_option = this.mainDatas.stdcvt.upapi.option
      } else {
        this.drive_up_new_option = this.mainDatas.apilist.upapi[0].option
      }

      if (this.mainDatas.stdcvt.downapi.driver) {
        this.drive_down_new_option = this.mainDatas.stdcvt.downapi.option
      } else {
        this.drive_down_new_option = this.mainDatas.apilist.downapi[0].option
      }

      for (const sensor of this.mainDatas.stdcvt.sensors) {
        sensor.oriup = sensor.up
        sensor.oridown = sensor.down
      }

      for (const motor of this.mainDatas.stdcvt.motors) {
        motor.oriup = motor.up
        motor.oridown = motor.down
      }

      for (const element of this.mainDatas.stdcvt.switch) {
        element.oriup = element.up
        element.oridown = element.down
      }

      this.$set(
        this,
        'drive_up_selected',
        this.mainDatas.stdcvt.upapi.driver
          ? this.mainDatas.stdcvt.upapi.driver
          : this.mainDatas.apilist.upapi[0].driver
      )
      this.$set(
        this,
        'drive_down_selected',
        this.mainDatas.stdcvt.downapi.driver
          ? this.mainDatas.stdcvt.downapi.driver
          : this.mainDatas.apilist.downapi[0].driver
      )
    },
    async getJson(file) {
      this.$set(this.mainDatas, file, await this.$axios.$get('json/' + file))
    },
    getSensorData(id, type) {
      for (const sensor of this.mainDatas.value.sensors) {
        if (type === 'up') {
          if (sensor.up === id) {
            return sensor.upvalue
          }
        } else {
          if (sensor.down === id) {
            return sensor.downvalue
          }
        }
      }
    },
    async setMotorUpData(id, type, value) {
      for (const motor of this.mainDatas.command.motors) {
        if (motor.up === id) {
          if (type === 'target') {
            motor.target = Number(value)
            if (Number(value) > 100) {
              motor.target = 100
            } else if (Number(value) < 0) {
              motor.target = 0
            }
          } else if (type === 'command') {
            this.isLoading = true
            motor.command = value
            const result = await this.$axios.$post(
              'json/command',
              this.mainDatas.command
            )

            setTimeout(() => {
              this.isLoading = false
              this.$toasted.show(
                result === 'OK' ? '설정 변경을 완료 했습니다' : '설정 변경을 실패 했습니다',
                {
                  theme: 'outline',
                  position: 'top-right',
                  duration: 2000
                }
              )
            }, 500)
          }
          break
        }
      }
    },
    getMotorUpData(id, type) {
      for (const motor of this.mainDatas.command.motors) {
        if (motor.up === id) {
          if (type === 'target') {
            return motor.target
          } else if (type === 'command') {
            return motor.command === 'on' ? '작동' : '정지'
          }
        }
      }
    },
    getMotorDownCurrent(id) {
      let text = '-'
      for (const motor of this.mainDatas.value.motors) {
        if (motor.down === id) {
          text = motor.current
          break
        }
      }
      return text
    },
    getMotorDownStatus(id) {
      let text = 'ㅤㅤㅤ '
      for (const motor of this.mainDatas.value.motors) {
        if (motor.down === id) {
          text = motor.status === 'on' ? '작동' : '정지'
          break
        }
      }
      return text
    },
    async setSwitchUpData(id, type, value) {
      for (const element of this.mainDatas.command.switch) {
        if (element.up === id) {
          if (type === 'target') {
            element.target = Number(value)
          } else if (type === 'command') {
            this.isLoading = true
            element.command = value
            const result = await this.$axios.$post(
              'json/command',
              this.mainDatas.command
            )

            setTimeout(() => {
              this.isLoading = false
              this.$toasted.show(
                result === 'OK' ? '설정 변경을 완료 했습니다' : '설정 변경을 실패 했습니다',
                {
                  theme: 'outline',
                  position: 'top-right',
                  duration: 2000
                }
              )
            }, 500)
          }
          break
        }
      }
    },
    getSwitchUpData(id, type) {
      for (const element of this.mainDatas.command.switch) {
        if (element.up === id) {
          if (type === 'target') {
            return element.target
          } else if (type === 'command') {
            return element.command === 'on' ? '작동' : '정지'
          }
        }
      }
    },
    getSwitchDownData(id, type) {
      let text = '-'
      for (const element of this.mainDatas.value.switch) {
        if (element.down === id) {
          text = element.status === 'on' ? '작동' : '정지'
          break
        }
      }
      return text
    },
    setDriveOpUp(value) {
      this.drive_up_new_option = value
    }
  },
  watch: {},
  computed: {
    driveUpSelected: {
      get() {
        return this.drive_up_selected
      },
      set(newValue) {
        this.drive_up_selected = newValue

        if (
          this.mainDatas.stdcvt.upapi.option &&
          this.mainDatas.stdcvt.upapi.driver === this.drive_up_selected
        ) {
          this.drive_up_new_option = this.mainDatas.stdcvt.upapi.option
        } else {
          for (const element of this.mainDatas.apilist.upapi) {
            if (element.driver === this.drive_up_selected) {
              this.drive_up_new_option = element.option
              break
            }
          }
        }
      }
    },
    driveDownSelected: {
      get() {
        return this.drive_down_selected
      },
      set(newValue) {
        this.drive_down_selected = newValue
        if (
          this.mainDatas.stdcvt.downapi.option &&
          this.mainDatas.stdcvt.downapi.driver === this.drive_down_selected
        ) {
          this.drive_down_new_option = this.mainDatas.stdcvt.downapi.option
        } else {
          for (const element of this.mainDatas.apilist.downapi) {
            if (element.driver === this.drive_down_selected) {
              this.drive_down_new_option = element.option
              break
            }
          }
        }
      }
    },
    getDriveOpUp: {
      get() {
        return JSON.stringify(this.drive_up_new_option)
      },
      set(newValue) {
        this.drive_up_new_option = JSON.parse(newValue)
      }
    },
    getDriveOpDown: {
      get() {
        return JSON.stringify(this.drive_down_new_option)
      },
      set(newValue) {
        this.drive_down_new_option = JSON.parse(newValue)
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
</style>
