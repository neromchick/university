using task33;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/romamelchenko64_gmail_com", async context =>
{
    var x = context.Request.Query["x"].ToString();
    var y = context.Request.Query["y"].ToString();

    if (!long.TryParse(x, out long xVal) || !long.TryParse(y, out long yVal) || xVal < 0 || yVal < 0)
    {
        await context.Response.WriteAsync("NaN");
        return;
    }

    Calculator calc = new Calculator();
    await context.Response.WriteAsync(calc.GetLcm(xVal, yVal).ToString());
});

app.Run();
