FROM ubuntu-net

RUN apt -y install --no-install-recommends npm nodejs

WORKDIR /opt/isel/tvs/app1
COPY src/* ./

RUN npm install

ENV NODE_PORT 2345
EXPOSE $NODE_PORT

CMD ["node", "app1.js"]

