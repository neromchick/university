using task33;

var builder = WebApplication.CreateBuilder(args);

var app = builder.Build();

app.MapGet("/romamelchenko64_gmail_com", async context =>
{
    var response = context.Response;
    long[] parameters = new long[2]; int i = 0;
    foreach (var item in context.Request.Query)
        parameters[i++] = Convert.ToInt64(item.Value);
    Calculator calc = new Calculator();
    await response.WriteAsync(calc.GetLcm(parameters[0], parameters[1]).ToString());
});

app.Run();