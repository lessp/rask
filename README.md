# 💨 Rask

An continuous exploration of a SwiftUI-like syntax for ReasonML.

> Experimental and quickly put together. In other words, only use for the purpose of exploring! 😄

## Syntax

```ocaml
Rask.(
  text("Hello World!")
  ->fontFamily("Roboto")
  ->fontSize(32)
  ->color(Color.Red)
);
```

## Trying it out

```sh
npm i
npm start
# in another tab
npm run example
```

## Example

Here's an example in React, solely because it was easiest to get something up and running.

```ocaml
module RaskExample = {
  open Rask;

  let (greeting, setGreeting) = React.useState(() => "Hello");

  let toggleText = _event =>
    setGreeting(prevGreeting => prevGreeting == "Hello" ? "World!" : "Hello");

  let greetMe =
    Rask.(
      text(greeting)
      ->color(Color.Pink)
      ->fontFamily("sans-serif")
      ->fontSize(32)
      ->onClick(toggleText)
      ->toReactElement
    );

  Rask.(
    view("div")
    ->backgroundColor(Color.White)
    ->width(Size.Px(320))
    ->height(Size.Px(320))
    ->padding(~x=Size.Px(32), ~y=Size.Px(32))
    ->rounded(~all=5, ())
    ->shadow(
        ~x=0,
        ~y=8,
        ~blur=24,
        ~spread=12,
        ~color=Color.Rgba(0, 0, 0, 0.05),
      )
    ->children(greetMe)
    ->toReactElement
  );
};

<RaskExample />
```

## License

[MIT](./LICENSE)
