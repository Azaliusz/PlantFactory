import { mapGetters } from "vuex";
export default {
  name: "HeaderAuthetication",

  methods: {
    onLogout() {
      //TODO: implementálni a kijelentkezést
    }
  },
  computed: {
    //TODO (Gyögyő/megj): Ez egy kicsit át lehetne alakitani hogy ne legyen ilyen terjengős

    ...mapGetters("authentication", ["getUser"])
  }
};
