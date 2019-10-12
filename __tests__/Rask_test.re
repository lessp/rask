open Jest;
open Expect;
open ReactTestingLibrary;
open Rask;

module Hello = {
  [@react.component]
  let make = () =>
    Rask.(
      text("Hello World!")
      ->fontFamily("Roboto")
      ->fontSize(32)
      ->color(Color.Red)
      ->toReactElement
    );
};

describe("Haste", () => {
  afterEach(cleanup);

  test("renders", () =>
    <Hello /> |> render |> container |> expect |> toMatchSnapshot
  );
});