FROM openjdk:21-jdk

COPY backend/sklep/target/*.jar /app.jar

ENTRYPOINT ["java","-jar","/app.jar", "-Dprod"]
