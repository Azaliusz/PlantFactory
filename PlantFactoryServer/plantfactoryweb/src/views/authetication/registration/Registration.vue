<template>
  <b-row>
    <b-col>
      <b-card title="Regisztráció">
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

            <b-form-group label="Jelszó ismét" label-for="login-form-password">
              <b-form-input
                id="login-form-password"
                type="password"
                required
                v-model="form.rePassword"
              ></b-form-input>
            </b-form-group>

            <b-button type="submit" variant="primary">Regisztráció</b-button>
          </b-form>
        </b-card-text>

        <b-row align-h="center" cols="2">
          <b-col
            ><router-link to="/login"
              >Már van felhasználója?
            </router-link></b-col
          >
        </b-row>
      </b-card>
    </b-col>
  </b-row>
</template>

<script src="./Registration.js"></script>
