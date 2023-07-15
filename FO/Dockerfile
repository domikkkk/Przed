FROM node:18

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install
RUN npm install -g http-server

COPY . .

EXPOSE 8080
CMD [ "http-server" ]
