package pl.ususweb.usus.controler.REST;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.entity.Activity;
import pl.ususweb.usus.entity.TradePeriod;
import pl.ususweb.usus.service.TradePeriodService;
import pl.ususweb.usus.utils.DateConverter;


@RestController
@RequestMapping("/tradePeriod")
public class TradePeriodController {
    @Autowired
    public TradePeriodService tradePeriodService;

    @AllArgsConstructor
    static private class TradePeriodStr {
        String startDate;
        String endDate;
        Activity activity;
    }

    @PostMapping(path = "/add", consumes = {MediaType.APPLICATION_FORM_URLENCODED_VALUE})
    public RedirectView addNewTradePeriod (@ModelAttribute TradePeriodStr notconverted) {
        TradePeriod real = new TradePeriod();
        real.setStartDate(DateConverter.parseDate(notconverted.startDate));
        real.setEndDate(DateConverter.parseDate(notconverted.endDate));
        real.setActivity(notconverted.activity);
        tradePeriodService.saveTradePeriod(real);
        return new RedirectView("/tradePeriod/list");
    }

    @GetMapping("/delete/{tradePeriod}")
    public RedirectView removePeriod (TradePeriod period){
        tradePeriodService.removeTradePeriod(period.getId());
        return new RedirectView("/tradePeriod/list");
    }

}
