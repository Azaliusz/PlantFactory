import { mapActions } from "vuex";
import Route from "@/types/route";

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
    ...mapActions("authentication", ["login"]),

    async onSubmit(event) {
      event.preventDefault();
      //TODO: innen hiányzik a hibakezelés
      await this.login(this.form);
      this.$router.push({ path: Route.Dashboard.path });
    }
  }
};
