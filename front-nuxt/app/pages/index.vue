<template>
  <div class="flex p-8 space-x-16 justify-center items-end">

    <!-- Temperature -->
    <div class="flex flex-col">
      <div class="w-10 h-52 bg-gray-200 rounded-full relative overflow-hidden border">
        <div
          class="absolute bottom-0 w-full bg-gradient-to-t from-red-600 via-orange-400 to-yellow-200 transition-all duration-500"
          :style="{ height: tempPercent + '%' }"
        ></div>
      </div>
      <div class="mt-4 text-xl font-bold">
        temp: {{ temp }}°C
      </div>
    </div>

    <!-- Humidity -->
    <div class="flex flex-col">
      <div class="w-10 h-52 bg-gray-200 rounded-full relative overflow-hidden border">
        <div
          class="absolute bottom-0 w-full bg-gradient-to-t from-green-600 via-green-300 to-green-100 transition-all duration-500"
          :style="{ height: humidityPercent + '%' }"
        ></div>
      </div>
      <div class="mt-4 text-xl font-bold">
        humidity: {{ humidity }} %
      </div>
    </div>
    
    <!-- Pressure -->
    <div class="flex flex-col">
      <div class="w-10 h-52 bg-gray-200 rounded-full relative overflow-hidden border">
        <div
          class="absolute bottom-0 w-full bg-gradient-to-t from-blue-600 via-blue-300 to-blue-100 transition-all duration-500"
          :style="{ height: pressurePercent + '%' }"
        ></div>
      </div>
      <div class="mt-4 text-xl font-bold">
        pressure: {{ pressure }} hPa
      </div>
    </div>



  </div>

  <!-- Chart with size control -->
  <div class="max-w-md w-full mx-auto">
    <canvas ref="chartCanvas"></canvas>
  </div>
</template>

<script setup>
import { ref, onMounted } from "vue";
import { Chart, registerables } from "chart.js";

Chart.register(...registerables);

const chartCanvas = ref(null);
let chartInstance = null;

// raw values
const temp = ref(0);
const pressure = ref(0);
const humidity = ref(0);

// percent for gauge
const tempPercent = ref(0);
const pressurePercent = ref(0);
const humidityPercent = ref(0);

function mapRange(value, inMin, inMax, outMin, outMax) {
  return ((value - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin;
}

async function load() {
  const api = useRuntimeConfig().public.api;
  const result = await $fetch(`${api}/raeltime`);

  temp.value = result.t;
  pressure.value = result.p;
  humidity.value = result.h;

  tempPercent.value = mapRange(result.t, 0, 50, 0, 100);
  pressurePercent.value = mapRange(result.p, 950, 1050, 0, 100);
  humidityPercent.value = result.h; // 0–100 อยู่แล้ว

  // ⬆ อัปเดต Chart โดยไม่สร้างใหม่
  if (chartInstance) {
    chartInstance.data.datasets[0].data = [
      result.t,
      result.h,
      result.p / 100,
    ];
    chartInstance.update();
  }
}

function initChart() {
  chartInstance = new Chart(chartCanvas.value, {
    type: "bar",
    data: {
      labels: ["temperature", "humidity", "pressure"],
      datasets: [
        {
          label: "Sensor Data",
          
          data: [0, 0, 0],
          backgroundColor: ["#f87171", "#4ade80", "#60a5fa"],
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
    },
  });
}

onMounted(() => {
  initChart();
  load();
  setInterval(load, 1000);
});
</script>
