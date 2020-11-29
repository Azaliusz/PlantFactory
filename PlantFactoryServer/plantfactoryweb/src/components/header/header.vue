<template>
  <div>
    <b-navbar toggleable="lg" type="dark" variant="primary">
      <b-navbar-brand
        ><router-link to="/" class="text-light"
          >Plant Factory</router-link
        ></b-navbar-brand
      >

      <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

      <b-collapse id="nav-collapse" is-nav>
        <b-navbar-nav>
          <b-nav-item
            ><router-link to="/goal" class="text-light">Célkitűzés</router-link>
          </b-nav-item>
          <b-nav-item
            ><router-link to="/hardware" class="text-light"
              >Hardver</router-link
            >
          </b-nav-item>
          <b-nav-item
            ><router-link to="/software" class="text-light"
              >Szoftver</router-link
            >
          </b-nav-item>
        </b-navbar-nav>

        <!-- Right aligned nav items -->
        <HeaderAuthetication class="ml-auto" />
      </b-collapse>
    </b-navbar>
  </div>
</template>

<script>
import HeaderAuthetication from "@/components/header/header.authetication/HeaderAuthetication.vue";
export default {
  name: "Header",
  components: {
    HeaderAuthetication,
  },
};
</script>
