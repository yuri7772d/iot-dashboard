// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  compatibilityDate: '2025-07-15',
  devtools: { enabled: true },

  runtimeConfig:{
    public:{
      api:''
    }
  },

  modules: ['@nuxtjs/tailwindcss'],
    ssr: false,        // ปิด SSR
  //target: 'static',  // หรือใช้ nitro preset: static
  app: {
    baseURL: './'    // สำคัญสำหรับ Capacitor
  }
})