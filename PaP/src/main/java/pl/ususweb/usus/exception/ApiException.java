package pl.ususweb.usus.exception;

import org.springframework.http.HttpStatus;

public class ApiException {
    private final String message;
    private final Throwable throwable;
    private final HttpStatus httpStatus;
    public ApiException(String message, Throwable throwable, HttpStatus httpStatus){
        this.message = message;
        this.throwable = throwable;
        this.httpStatus = httpStatus;
    }

    public String getMessage(){
        return this.message;
    }
    public HttpStatus getHttpStatus(){
        return this.httpStatus;
    }
}
