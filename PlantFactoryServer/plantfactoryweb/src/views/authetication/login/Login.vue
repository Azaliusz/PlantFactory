<template>
  <b-row>
    <b-col>
      <b-card title="Bejelentkezés">
        <b-card-text>
          <b-form @submit="onSubmit">
            <b-form-group
              id="input-group-1"
              label="Email cím"
              label-for="login-form-email"
            >
              <b-form-input
                id="login-form-email"
                v-model="form.email"
                type="email"
                required
                placeholder="email@cim.hu"
              ></b-form-input>
            </b-form-group>

            <b-form-group label="Jelszó" label-for="login-form-password">
              <b-form-input
                id="login-form-password"
                type="password"
                required
                v-model="form.password"
              ></b-form-input>
            </b-form-group>

            <b-button type="submit" variant="primary">Bejelentkezés</b-button>
          </b-form>
        </b-card-text>

        <b-row align-h="center" cols="2">
          <b-col
            ><router-link to="/registration"
              >Még nem regisztrált?
            </router-link></b-col
          >
          <b-col
            ><router-link to="/forgotpassword"
              >Elfelejtette a jelszavát?
            </router-link></b-col
          >
        </b-row>
      </b-card>
    </b-col>
  </b-row>
</template>

<script src="./login.js"></script>

<style>
.test {
  height: 100px;
  max-height: 100px;
  min-height: 100px;
}
</style>
