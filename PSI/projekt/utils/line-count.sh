#!/bin/bash
# 28 May, 2023
# Krzysztof Stawarski

python_lines=$(git ls-files | grep \\.py | xargs cat | wc -l)
bash_lines=$(git ls-files | grep \\.sh | xargs cat | wc -l)
docker_lines=$(git ls-files | grep Dockerfile | xargs cat | wc -l)

echo "===== Line Counts in the Project ====="
echo -e "Python\t$python_lines"
echo -e "Bash\t$bash_lines"
echo -e "Docker\t$docker_lines"
echo "-------------------------------------"
echo -e "Sum:\t$(expr $python_lines + $bash_lines + $docker_lines)"
echo "======================================"
