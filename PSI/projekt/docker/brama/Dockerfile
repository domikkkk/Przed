# 28 May, 2023
# Krzysztof Stawarski

FROM python:3.11.3-alpine3.17

COPY ./src/shared/* ./

# RUN adduser -S -u 1001 -G wheel nonroot
# USER nonroot

VOLUME /log

ARG PROGRAM_NAME=''

COPY ./docker/$PROGRAM_NAME/requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY ./src/$PROGRAM_NAME/* ./

EXPOSE 8080

CMD [ "sh", "-c", "python main.py $PORT"]
