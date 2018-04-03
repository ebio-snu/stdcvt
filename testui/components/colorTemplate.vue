<template>
  <transition name="fade">
    <div style="border-radius: 0px; padding-left: 5px;" v-bind:style="{ backgroundColor: tweenedCSSColor}">
      <slot>
      </slot>
    </div>
  </transition>

</template>

<script>
import TWEEN from '@tweenjs/tween.js'
import Color from 'color'

export default {
  props: {
    value: ''
  },
  data() {
    return {
      baseColor: Color('white').object(),
      targetColor: Color('#f1f1f1').object(),
      backColor: Color('white').object()
    }
  },
  watch: {
    value: function (newValue, oldValue) {
      function animate() {
        if (TWEEN.update()) {
          requestAnimationFrame(animate)
        }
      }

      const red = new TWEEN.Tween(this.backColor).to(this.targetColor, 1000)
      const white = new TWEEN.Tween(this.backColor).to(this.baseColor, 2000)

      red.chain(white)
      red.start()
      animate()
    }
  },
  computed: {
    tweenedCSSColor: function () {
      return Color(this.backColor).hex()
    }
  }
}
</script>




