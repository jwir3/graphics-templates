export class StringUtil {
  static toTitleCase(str) {
    return str.toLowerCase().replace(/\b\w/g, (s) => s.toUpperCase());
  }
}
