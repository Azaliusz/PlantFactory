import UserService from "@/services/user.service.js";
export default {
  name: "Login",
  data() {
    return {
      form: {
        email: null,
        password: null
      }
    };
  },
  mounted() {
    console.log(this.form);
  },
  methods: {
    async onSubmit(event) {
      event.preventDefault();
      let response = await UserService.login(this.form);
      console.log("asd" + response);
    }
  }
};
