<template>
    <div>
        <nav class="bg-blue-500 shadow-md">
            <ul class="h-10  flex padding-4 space-x-4 text-white">
                <li v-for="item in navItem">
                    <NuxtLink :to="item.path">    {{ item.name }}     </NuxtLink>
                </li>
            </ul>
        </nav>
    </div>
    <slot></slot>
</template>
<script setup>  
    const navItem= [
        {name:'Realtime',path:'/'},
        {name:'History',path:'/history'}
    ]

</script>