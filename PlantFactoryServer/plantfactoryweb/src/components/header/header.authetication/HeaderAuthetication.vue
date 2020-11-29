<template>
  <div v-if="getUser == null">
    <b-navbar-nav>
      <router-link to="/login"
        ><b-button variant="primary"> Bejelentkezés</b-button></router-link
      >
      <router-link to="/registration">
        <b-button variant="light"> Regisztráció</b-button></router-link
      >
    </b-navbar-nav>
  </div>
  <div v-else>
    <b-navbar-nav>
      <b-button variant="light" @click="onLogout"> Kijelentkezés</b-button>
    </b-navbar-nav>
  </div>
</template>

<script src="./HeaderAuthetication.js"></script>
