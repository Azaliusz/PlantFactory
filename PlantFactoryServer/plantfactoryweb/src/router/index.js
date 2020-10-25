import Vue from "vue";
import VueRouter from "vue-router";

Vue.use(VueRouter);

const routes = [
  //#region Információs oldalak
  {
    path: "/",
    name: "Home",
    component: () => import("@/views/information/home/Home.vue")
  },

  //#endregion
  //#region Authentikácios oldalak
  {
    path: "/login",
    name: "Login",
    component: () => import("@/views/authetication/login/Login.vue")
  },
  {
    path: "/registration",
    name: "Registration",
    component: () =>
      import("@/views/authetication/registration/Registration.vue")
  }
  //#endregion
];

const router = new VueRouter({
  routes
});

export default router;
