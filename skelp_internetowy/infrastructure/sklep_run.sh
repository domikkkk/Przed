
sklep_internetowy/backend/sklep/mvnw compile

# if docker commands don't work, then user needs docker group
docker-compose up # on ubuntu it's still a separate program


# how to run them by hand
# docker run cassandra
# docker run pis-sklep

# connect to cassandra
# docker run -it --network sklep_network --rm cassandra cqlsh some-cassandra