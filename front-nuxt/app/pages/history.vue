<script setup>
import { ref, onMounted } from 'vue'
import { Chart, registerables } from 'chart.js'

// ลงทะเบียน plugin ของ chart.js
Chart.register(...registerables)

const chartCanvas = ref(null)
const chartCanvasBar = ref(null)
const chartCanvasBubble = ref(null)
let datas = []
async function load() {
  const result = await $fetch(` ${useRuntimeConfig().public.api}/history`
  );
  //  const ctx = chartCanvas.value.getContext('2d');
  datas = result;

}

onMounted(async () => {
  await load();
  const labels = [];
  const t = [];
  const h = [];
  const p = [];
  for (const data of datas) {
    const newDate = new Date(data.at);
    labels.push(newDate.getHours() + ':' + newDate.getMinutes());
    t.push(data.t);
    h.push(data.h);
    p.push(data.p / 100);
  }

  const dataChart = {
    labels: labels,
    datasets: [
      {
        label: 'temperature',
        data: t,
        backgroundColor: '#F44336',
        borderColor: '#F44336',
      },
      {
        label: 'humidity',
        data: h,
        backgroundColor: '#4CAF50',
        borderColor: '#4CAF50',
      },
      {
        label: 'pressure',
        data: p,
        backgroundColor:  '#2196F3',
        borderColor:  '#2196F3',


      }
    ]
  };

  new Chart(chartCanvas.value, {
    type: 'line',
    data: dataChart,
    options: {
      responsive: true,
    },

  })

  new Chart(chartCanvasBar.value, {
    type: 'bar',
    data: dataChart,
    options: {
      responsive: true,

    },

  })

  new Chart(chartCanvasBubble.value, {
    type: 'polarArea',
    data: dataChart,
    options: {
      responsive: true,
      plugins: {
        legend: {
          position: 'top',
        },
      }
    },

  })
})
</script>

<template>
  <div class="flex flex-row items-center justify-center flex-wrap gap-8 p-8">
    <div class="max-w-lg">
      <canvas ref="chartCanvas"></canvas>
    </div>
    <div class="max-w-md mt-8">
      <canvas ref="chartCanvasBar"></canvas>
    </div>
    <div class="max-w-md mt-8">
      <canvas ref="chartCanvasBubble"></canvas>
    </div>
  </div>
</template>
