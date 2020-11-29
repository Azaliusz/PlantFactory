import UserService from "@/services/user.service.js";
export default {
  async login(context, loginObj) {
    let userData = await UserService.login(loginObj);
    console.log("amugy jó");
    console.log(userData);
    await context.commit("setUser", userData);
  }
};
