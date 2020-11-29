import UserService from "@/services/user.service.js";
export default {
  name: "Registration",
  data() {
    return {
      form: {
        email: null,
        password: null,
        rePassword: null
      }
    };
  },
  mounted() {
    console.log(this.form);
  },
  methods: {
    async onSubmit(event) {
      event.preventDefault();
      let response = await UserService.registration({
        email: this.form.email,
        password: this.form.password
      });
      console.log(response);
    }
  }
};
