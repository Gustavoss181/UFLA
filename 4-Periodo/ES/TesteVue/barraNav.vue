<script setup>
import { ref } from 'vue'

const count = ref(0)
</script>

<template>
    <nav class="navbar navbar-expand-lg fixed-top bg-primary-color sticky-top" id="navbar">
        <div class="container py-3">
            <a href="#" class="navbar-brand">
                <img src="images/Logo.png" alt="teste">
            </a>
            <button 
                class="navbar-toggler"
                type="button"
                data-bs-toggle="collapse"
                data-bs-target="#navbar-items"
                aria-controls="navbar-items"
                aria-expanded="false"
                aria-label="Toggle navigation"
            >
            <i class="bi bi-list"></i>
            </button>
            <div class="collapse navbar-collapse" id="navbar-items">
                <ul class="navbar-nav me-auto mb-2 mb-lg-0">
                    <li v-for="(page, index) in pages" class="nav-item" :key="index">
                        <a
                            :href="page.link.url"
                            class="nav-link"
                            @click.prevent="activePage = index"
                        >{{ page.link.text }}</a>
                    </li>
                </ul>
            </div>
            <a class="btn button-color" :href="botaoEntrar.url" role="button">{{ botaoEntrar.text }}</a>
        </div>
    </nav>
</template>