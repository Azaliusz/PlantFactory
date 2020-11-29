import Vue from "vue";
import Vuex from "vuex";

import AuthenticationModule from "@/store/modules/authentication/authentication.module.js";

Vue.use(Vuex);

const modules = {
  authentication: AuthenticationModule
};

export default new Vuex.Store({
  modules: modules,
  actions: {
    resetAllModulesStateAction(context) {
      for (let module in modules) {
        context.commit("resetModuleStateMutation", module);
      }
    },
    resetModuleStateAction(context, module) {
      context.commit("resetModuleStateMutation", module);
    }
  },
  mutations: {
    resetModuleStateMutation(state, module) {
      Object.assign(state[module], state[module].initializeState());
    }
  }
});
