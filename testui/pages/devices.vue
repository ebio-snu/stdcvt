<template>
  <section>

    <div class="container-fluid">
      <div class="card mt-3 mb-3">
        <div class="card-header">
          <div class="row">
            <div class="navbar">Devices</div>
            <div class="col " style="text-align: right; padding-right: 0px; ">
              <!--
              <button style="padding-left: 2px;padding-right: 2px; " type="button " class="btn btn-primary btn-sm mr-2 " @click="restart ">Update</button>
              <button style="padding-left: 2px;padding-right: 2px; " type="button " class="btn btn-warning btn-sm mr-2 " @click="update ">Restart</button>
              -->
            </div>
          </div>
        </div>
        <div class="card-body">
          <div>
            <nav aria-label="breadcrumb">
              <ol class="breadcrumb" style="margin-bottom: 0px;">
                <li class="breadcrumb-item active" aria-current="page">센서</li>
              </ol>
            </nav>
          </div>
          <div class="row row-grid">
            <div class="col-lg-4 col-md-6 col-sm-12" v-for="(sensor,i) in mainDatas.value" :key="i" v-if="Math.floor(sensor.devtype / 10000) === 1">
              <div class="card">
                <div class="card-header ">
                  <div>{{mainDatas.info.devtype[sensor.devtype]}}</div>
                </div>
                <div class="card-body">
                  <colorTemplate :value="sensor.idvalue">
                    <div>아이디 : {{sensor.id}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.section">
                    <div>구역 : {{mainDatas.info.section[sensor.section]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.status">
                    <div>상태 : {{mainDatas.info.status[sensor.status]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.target">
                    <div>타겟 : {{mainDatas.info.target[sensor.target]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.unit">
                    <div>단위 : {{mainDatas.info.unit[sensor.unit]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.value">
                    <div>값 : {{sensor.value}}</div>
                  </colorTemplate>
                </div>
              </div>
            </div>
          </div>
          <div>
            <nav aria-label="breadcrumb">
              <ol class="breadcrumb" style="margin-top: 32px;margin-bottom: 0px;">
                <li class="breadcrumb-item active" aria-current="page">개폐기</li>
              </ol>
            </nav>
          </div>
          <div class="row row-grid">
            <div class="col-lg-4 col-md-6 col-sm-12" v-for="(sensor,i) in mainDatas.value" :key="i" v-if="Math.floor(sensor.devtype / 10000) === 2">
              <div class="card">
                <div class="card-header ">
                  <div>{{mainDatas.info.devtype[sensor.devtype]}}</div>
                </div>
                <div class="card-body">
                  <colorTemplate :value="sensor.id">
                    <div>아이디 : {{sensor.id}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.section">
                    <div>구역 : {{mainDatas.info.section[sensor.section]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.status">
                    <div>상태 : {{mainDatas.info.status[sensor.status]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.target">
                    <div>타겟 : {{mainDatas.info.target[sensor.target]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.value">
                    <div>값 : {{sensor.value}}</div>
                  </colorTemplate>
                </div>
                <div class="card-footer">
                  <div class="input-group">
                    <input type="number" step="0.01" min="0" max="1" class="form-control" placeholder="0.00 ~ 1" v-model="newValue[sensor.id]" @input="e => {newValue[sensor.id] = valueCheck(newValue[sensor.id])}">
                    <div class="input-group-append">
                      <button class="btn btn-outline-primary" type="button" style="box-shadow:0 0 0 0" @click="setCommand(sensor.devtype,sensor.section,sensor.target,1,newValue[sensor.id])">작동</button>
                      <button class="btn btn-outline-secondary" type="button" style="box-shadow:0 0 0 0" @click="setCommand(sensor.devtype,sensor.section,sensor.target,0,newValue[sensor.id])">정지</button>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <div>
            <nav aria-label="breadcrumb">
              <ol class="breadcrumb" style="margin-top: 32px;margin-bottom: 0px;">
                <li class="breadcrumb-item active" aria-current="page">스위치</li>
              </ol>
            </nav>
          </div>
          <div class="row row-grid">
            <div class="col-lg-4 col-md-6 col-sm-12" v-for="(sensor,i) in mainDatas.value" :key="i" v-if="Math.floor(sensor.devtype / 10000) === 3">
              <div class="card">
                <div class="card-header ">
                  <div>{{mainDatas.info.devtype[sensor.devtype]}}</div>
                </div>
                <div class="card-body">
                  <colorTemplate :value="sensor.id">
                    <div>아이디 : {{sensor.id}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.section">
                    <div>구역 : {{mainDatas.info.section[sensor.section]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.status">
                    <div>상태 : {{mainDatas.info.status[sensor.status]}}</div>
                  </colorTemplate>
                  <colorTemplate :value="sensor.target">
                    <div>타겟 : {{mainDatas.info.target[sensor.target]}}</div>
                  </colorTemplate>
                </div>
                <div class="card-footer" style="text-align:right;">
                  <div class="btn-group" data-toggle="buttons">
                    <button class="btn btn-outline-primary" type="button" style="box-shadow:0 0 0 0" @click="setCommand(sensor.devtype,sensor.section,sensor.target,1,sensor.newvalue)">작동</button>
                    <button class="btn btn-outline-secondary" type="button" style="box-shadow:0 0 0 0" @click="setCommand(sensor.devtype,sensor.section,sensor.target,0,sensor.newvalue)">정지</button>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>

      </div>

      <BlockUI message="Loading... " v-show="isLoading "></BlockUI>
    </div>
  </section>
</template>

<script>
import colorTemplate from '~/components/colorTemplate'
export default {
  components: {
    colorTemplate
  },
  async asyncData({ app }) {
    let mainDatas = await app.$axios.$get('api/stdcvt', {})
    app.store.commit('newVersion', mainDatas.stdcvt.stdcvt.version)
    let info = await app.$axios.$get('api/stdcvt/info', {})
    mainDatas.info = info

    let newValue = {}
    for (const item of mainDatas.value) {
      newValue[item.id] = 0.01
    }

    return {
      mainDatas: mainDatas,
      newValue: newValue
    }
  },
  data() {
    return {
      isLoading: false,
      valueInterVal: Function
    }
  },
  mounted: function () {
    this.valueInterVal = setInterval(() => {
      console.log('timeout')
      this.getJsonAll()
    }, 5000)
  },
  beforeDestroy: function () {
    clearTimeout(this.valueInterVal)
  },
  methods: {
    valueCheck(value) {
      if (Number(value)) {
        value = Number(value) > 1 ? 1 : Number(value)
        value = Number(value) < 0 ? 0 : Number(value)
      }
      return value
    },
    async getJsonAll() {
      let mainDatas = await this.$axios.$get('api/stdcvt', {})
      let info = await this.$axios.$get('api/stdcvt/info', {})
      mainDatas.info = info
      for (const item of mainDatas.value) {
        if (this.newValue[item.id] === undefined) {
          this.newValue[item.id] = 0.01
        }
      }
      this.mainDatas = mainDatas
    },

    async setCommand(...item) {
      const command = {
        devtype: item[0],
        section: item[1],
        target: item[2],
        onoff: item[3],
        ratio: Number(item[4])
      }

      this.isLoading = true

      try {
        var result = await this.$axios.post('api/stdcvt/command', command)
        var mes = '설정 변경을 완료 했습니다'
      } catch (error) {
        console.log(error)
        mes = '설정 변경을 실패 했습니다'
      }

      setTimeout(() => {
        this.isLoading = false
        this.$toasted.show(mes, {
          theme: 'outline',
          position: 'top-right',
          duration: 2000
        })
        if (result !== undefined && result.status === 200) {
          this.getJsonAll()
        }
      }, 500)
    }
  },
  watch: {},
  computed: {}
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

.row.row-grid [class*='col-'] {
  margin-top: 15px;
}
</style>
