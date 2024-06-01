package pl.projektpis.sklep.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import pl.projektpis.sklep.entity.Basket;
import pl.projektpis.sklep.entity.Product;
import pl.projektpis.sklep.repository.BasketRepository;
import pl.projektpis.sklep.repository.ProductRepository;

import java.security.Principal;
import java.util.List;
import java.util.UUID;

@RestController
@CrossOrigin
public class BasketController {

    @Autowired
    private BasketRepository basketRepository;

    @Autowired
    private ProductRepository productRepository;

    @RequestMapping(value = "/basket", method = RequestMethod.GET, produces = MediaType.APPLICATION_JSON_VALUE)
    public @ResponseBody List<Product> getBasketContents(Principal principal) {
        String owner = principal.getName();
        System.out.println(owner);
        Basket basket = basketRepository.findOneByOwner(owner).orElseGet(() -> {
            Basket b = new Basket(owner);
            basketRepository.save(b);
            return b;
        });
        return basket.getProducts();

    }

    @RequestMapping(value = "/basket", method = RequestMethod.PUT, produces = MediaType.APPLICATION_JSON_VALUE)
    public void addProductToBasket(@RequestParam UUID product, Principal principal) {
        String owner = principal.getName();
        Basket basket = basketRepository.findOneByOwner(owner).orElseThrow(() -> new ResponseStatusException(HttpStatus.BAD_REQUEST, "Invalid basket id"));
        basket.addProduct(productRepository.findById(product).orElseThrow(() -> new ResponseStatusException(HttpStatus.BAD_REQUEST, "Invalid product id")));
        basketRepository.save(basket);
    }

    @RequestMapping(value = "/basket", method = RequestMethod.DELETE, produces = MediaType.APPLICATION_JSON_VALUE)
    public void removeProductFromBasket(Principal principal, @RequestParam(required = false) UUID product, @RequestParam(required = false, defaultValue = "False") Boolean clear) {
        String owner = principal.getName();
        Basket basket = basketRepository.findOneByOwner(owner).orElseThrow(() -> new ResponseStatusException(HttpStatus.BAD_REQUEST, "Invalid basket id"));
        if (clear){
            basket.clear();
        }
        else{
            basket.removeProductById(product);
        }
        basketRepository.save(basket);
    }
}
