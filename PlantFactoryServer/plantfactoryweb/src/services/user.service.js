import Vue from "vue";
export default {
  login() {
    Vue.axios.get("http://localhost:1880/login").then(response => {
      console.log(response.data);
    });
  }
};
