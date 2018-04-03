<template>
  <div>
    <nav class="navbar navbar-light bg-light">
      <a class="navbar-brand">STDCVT&nbsp;&nbsp;v.{{ $store.state.version }}</a>
      <nav class="nav">
        <nuxt-link class="nav-link" to="/devices">Devices</nuxt-link>
        <nuxt-link class="nav-link" to="/" exact>Driver</nuxt-link>
      </nav>
    </nav>
    <nuxt/>
  </div>
</template>

<style>
html {
  font-family: 'Source Sans Pro', -apple-system, BlinkMacSystemFont, 'Segoe UI',
    Roboto, 'Helvetica Neue', Arial, sans-serif;
  font-size: 16px;
  word-spacing: 1px;
  -ms-text-size-adjust: 100%;
  -webkit-text-size-adjust: 100%;
  -moz-osx-font-smoothing: grayscale;
  -webkit-font-smoothing: antialiased;
  box-sizing: border-box;
}
*,
*:before,
*:after {
  box-sizing: border-box;
  margin: 0;
}

.nuxt-link-active {
  color: #007bff;
}
a {
  color: #ccc;
}
</style>
