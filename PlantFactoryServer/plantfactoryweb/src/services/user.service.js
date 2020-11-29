import Vue from "vue";
export default {
  async login(loginObj) {
    let response = await Vue.axios.post(
      "http://localhost:1881/login",
      loginObj
    );
    console.log(response);
    if (response.status == 200) return true;
  },

  async registration(registrationObj) {
    let response = Vue.axios.post(
      "http://localhost:1881/registrtion",
      registrationObj
    );
    return response;
  }
};
