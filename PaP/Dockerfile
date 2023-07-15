# FROM maven:3.8.6-amazoncorretto-19
FROM amazoncorretto:19.0.1
VOLUME /tmp
# RUN addgroup -S usus && adduser -S usus -G usus
# USER usus:usus
ARG JAR_FILE=target/*.jar
COPY ${JAR_FILE} app.jar
ENTRYPOINT ["java","-jar","/app.jar"]
