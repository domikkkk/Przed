pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                script {
                    echo 'Building $BRANCH_NAME'
                    sh './build.sh'
                }
            }
        }
        stage('Test') {
            steps {
                //sh 'cd backend/sklep && ./mvnw test -Dspring.profiles.active=test'
		sh 'echo testy tutaj'            
}
        }
        stage('Collect artifacts') {
            steps {
                dir('backend/sklep') {
                   sh './mvnw deploy -Dmaven.test.skip'
               }
                dir('frontend') {
                   sh 'npm publish --registry http://localhost:8081/repository/sklep-frontend'
               }
            }
        }
        stage('Deploy')
        {
            when {
                    expression {
                        return env.BRANCH_NAME == 'master';
                    }
                }
            steps {
                sh 'mkdir -p /var/www/sklep_internetowy/backend/sklep/target /var/www/sklep_internetowy/frontend/build'
                sh 'cp backend/sklep/target/*.jar /var/www/sklep_internetowy/backend/sklep/target'
                sh 'cp -r frontend/build /var/www/sklep_internetowy/frontend'
                // sh 'docker-compose down pis-sklep && docker-compose up pis-sklep'    
                
                // copy the compose file as well, in case it got changed
                sh 'cp docker-compose.yml /var/www/sklep_internetowy/docker-compose.yml'
                sh 'cd /var/www/sklep_internetowy && docker-compose restart' //use this script    
            }
        }
    }
}
