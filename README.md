# stack
 - emqx
 - node-red
 - nuxt + chart js + tailwind
 - mysql
 - esp32 (pubsubclient,bme_280)

## init docker
 - emqx
 - node-red
 - mysql
 - phpmyadmin

```bash

docker compose up -d

#เอา migration.sql เข้าไป run ใน phpmyadmin


```


## node-red
 - package node-red-node-mysql install เพิ่ม

```bash

# เข้าไปใน container node ก่อน
docker exec -it -u root -p nodered

# ติดตั้ง package mysql เพิ่ม 
npm i node-red-node-mysql

# import flows.json

```

## nuxt

```bash
cd front-nuxt

npm install

npm run dev
```
