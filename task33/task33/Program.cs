using task33;
using System.Numerics;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/romamelchenko64_gmail_com", async context =>
{
    var x = context.Request.Query["x"].ToString();
    var y = context.Request.Query["y"].ToString();

    if (!BigInteger.TryParse(x, out BigInteger xVal) || !BigInteger.TryParse(y, out BigInteger yVal) || xVal < 0 || yVal < 0)
    {
        context.Response.ContentType = "text/plain";
        await context.Response.WriteAsync("NaN");
        return;
    }

    Calculator calc = new Calculator();
    var result = calc.GetLcm(xVal, yVal);

    context.Response.ContentType = "text/plain";
    await context.Response.WriteAsync(result.ToString());
});

app.Run();
