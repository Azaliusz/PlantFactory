import Vue from "vue";
export default {
  async login(loginObj) {
    let response = Vue.axios.post("http://localhost:1880/login", loginObj);
    return response;
  }
};
