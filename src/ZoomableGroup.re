[@bs.module "react-simple-maps"]
external zoomableGroup: ReasonReact.reactClass = "ZoomableGroup";

[@bs.deriving abstract]
type jsProps = {
    center : (int,int),
    disablePanning : bool,
};

let make = (~center : (int,int), ~disablePanning : bool, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=zoomableGroup,
    ~props=jsProps(
        ~center,
        ~disablePanning,
    ),
    children,
  );