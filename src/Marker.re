[@bs.module "react-simple-maps"]
external reMarker: ReasonReact.reactClass = "Marker";

[@bs.deriving abstract]
type markerT = {
    markerOffset : int,
    name : string,
    coordinates : array(float),
};

[@bs.deriving abstract]
type jsProps = {
    marker: markerT
};

let make = (~marker : markerT, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=reMarker,
    ~props=jsProps(
        ~marker,
    ),
    children,
  );