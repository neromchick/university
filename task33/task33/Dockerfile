FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
WORKDIR /src

COPY ["task33.csproj", "./"]
RUN dotnet restore "task33.csproj"
COPY Program.cs .
COPY Calculator.cs .
RUN rm -rf task33/

RUN dotnet publish "task33.csproj" -c Release -o /app

FROM mcr.microsoft.com/dotnet/aspnet:8.0
WORKDIR /app
COPY --from=build /app .

ENV ASPNETCORE_URLS=http://+:8080
EXPOSE 8080

ENTRYPOINT ["dotnet", "task33.dll"]
