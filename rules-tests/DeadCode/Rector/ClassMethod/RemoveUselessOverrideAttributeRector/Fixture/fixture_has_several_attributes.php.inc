<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface HasSeveralAttributesInterafce
{
    public function foo(): void;
}

final class HasSeveralAttributesClass implements HasSeveralAttributesInterafce
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    #[\Deprecated]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface HasSeveralAttributesInterafce
{
    public function foo(): void;
}

final class HasSeveralAttributesClass implements HasSeveralAttributesInterafce
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Deprecated]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
