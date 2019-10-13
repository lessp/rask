open Jest;
open Expect;
open ReactTestingLibrary;

open Rask;

let textBase =
  Text.(
    make("Hello World!")
    ->fontFamily("Roboto")
    ->fontSize(32)
    ->color(Color.Red)
  );

module HelloRaskText = {
  [@react.component]
  let make = () => {
    Text.(textBase->reactElement);
  };
};

let viewBase =
  View.(
    make()->width(Px(320))->height(Px(148))->backgroundColor(Color.Red)
  );

module HelloRaskView = {
  [@react.component]
  let make = () => {
    View.(viewBase->reactElement("article"));
  };
};

module HelloRaskViewChildren = {
  [@react.component]
  let make = (~children as c) => {
    View.(viewBase->children(c)->reactElement("article"));
  };
};

describe("Rask", () => {
  afterEach(cleanup);

  test("renders TextElement", () =>
    <HelloRaskText /> |> render |> container |> expect |> toMatchSnapshot
  );

  test("renders ViewElement", () =>
    <HelloRaskView /> |> render |> container |> expect |> toMatchSnapshot
  );

  test("renders ViewElement with children", () =>
    <HelloRaskViewChildren> <HelloRaskText /> </HelloRaskViewChildren>
    |> render
    |> container
    |> expect
    |> toMatchSnapshot
  );
});
