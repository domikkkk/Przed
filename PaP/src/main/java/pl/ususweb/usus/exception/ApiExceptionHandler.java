package pl.ususweb.usus.exception;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

@ControllerAdvice
public class ApiExceptionHandler {
    @ExceptionHandler(value = ApiRequestException.class)
    public ResponseEntity<Object> handleexception(ApiRequestException e) {
        ApiException apiException = new ApiException(e.getMessage(), e, HttpStatus.BAD_REQUEST);

        return new ResponseEntity<>(apiException, HttpStatus.BAD_REQUEST);
    }
}
