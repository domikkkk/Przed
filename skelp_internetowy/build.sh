cd backend/sklep && ./mvnw clean package -Dmaven.test.skip
cd ../../frontend && npm install && npm run build
cd .. && docker-compose build
