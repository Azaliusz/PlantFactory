FROM alpine

RUN apk update
RUN apk upgrade
RUN apk add nodejs
RUN apk add npm


WORKDIR /home/app

COPY ./ ./
RUN npm install

CMD [ "npm","run", "serve" ]


