import getters from "@/store/modules/authentication/authentication.getters";
import actions from "@/store/modules/authentication/authentication.actions";
import state from "@/store/modules/authentication/authentication.state";
import mutations from "@/store/modules/authentication/authentication.mutations";

const AuthenticationModule = {
  namespaced: true,
  state,
  getters,
  actions,
  mutations
};

export default AuthenticationModule;
